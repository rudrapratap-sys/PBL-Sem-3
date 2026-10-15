import json
import os
import sys
import pickle
import pandas as pd

MODEL_FILE = "knn_opportunity_model.pkl"
OUTPUT_FILE = "prediction.txt"
SKILLS_INPUT_FILE = "student_skills.json"
TOP_N = 15


def load_student_skills():
    """Read skills like {"Python": 7, "pandas": 5} from a JSON file."""
    if not os.path.exists(SKILLS_INPUT_FILE):
        raise FileNotFoundError(
            f"{SKILLS_INPUT_FILE} not found. Create it with the student's skills."
        )

    with open(SKILLS_INPUT_FILE, "r", encoding="utf-8") as file:
        skills = json.load(file)

    if not isinstance(skills, dict):
        raise ValueError("student_skills.json must contain a JSON object.")

    cleaned = {}
    for name, score in skills.items():
        try:
            score = float(score)
        except (TypeError, ValueError):
            continue
        if 0 <= score <= 10:
            cleaned[str(name)] = score
    return cleaned


def main():
    # Clear the old prediction file every run, even if there is an error.
    with open(OUTPUT_FILE, "w", encoding="utf-8") as output:
        output.write("TOP 15 CLOSEST OPPORTUNITIES\n")
        output.write("============================\n\n")

    if not os.path.exists(MODEL_FILE):
        raise FileNotFoundError(
            f"{MODEL_FILE} not found. Run train.py first."
        )

    with open(MODEL_FILE, "rb") as file:
        bundle = pickle.load(file)

    model = bundle["model"]
    skill_columns = bundle["skill_columns"]
    opportunity_ids = bundle["opportunity_ids"]
    training_vectors = bundle["training_vectors"]

    student_skills = load_student_skills()

    # Default every skill column to 0, then fill skills provided by the student.
    student_vector = [0.0] * len(skill_columns)
    column_index = {name: i for i, name in enumerate(skill_columns)}

    unknown_skills = []
    for skill, score in student_skills.items():
        if skill in column_index:
            student_vector[column_index[skill]] = score
        else:
            unknown_skills.append(skill)

    distances, indices = model.kneighbors(
        [student_vector],
        n_neighbors=min(TOP_N, len(opportunity_ids))
    )

    # Load original opportunity details if the original CSV is available.
    details = {}
    possible_files = [
        "opportunities_200.csv",
        "knn_opportunity_dataset.csv",
        "opportunity_skill_features.csv",
    ]
    for filename in possible_files:
        if os.path.exists(filename):
            try:
                original = pd.read_csv(filename)
                if "opportunity_id" in original.columns:
                    details = {
                        str(row["opportunity_id"]): row
                        for _, row in original.iterrows()
                    }
                    break
            except Exception:
                pass

    with open(OUTPUT_FILE, "w", encoding="utf-8") as output:
        output.write("TOP 15 CLOSEST OPPORTUNITIES\n")
        output.write("============================\n\n")
        output.write("Student skills: ")
        output.write(", ".join(f"{k}:{v:g}" for k, v in student_skills.items()) or "None provided")
        output.write("\n\n")

        if unknown_skills:
            output.write(
                "Ignored unknown skills (not in the trained columns): "
                + ", ".join(unknown_skills) + "\n\n"
            )

        for rank, (distance, index) in enumerate(
            zip(distances[0], indices[0]), start=1
        ):
            opportunity_id = opportunity_ids[index]
            output.write(f"{rank}. Opportunity ID: {opportunity_id}\n")
            output.write(f"   Skill distance: {distance:.3f}\n")

            row = details.get(opportunity_id)
            if row is not None:
                for column in ["name", "category", "location", "min_gpa", "description"]:
                    if column in row.index and pd.notna(row[column]):
                        label = {
                            "name": "Name",
                            "category": "Category",
                            "location": "Location",
                            "min_gpa": "Minimum GPA",
                            "description": "Description",
                        }[column]
                        output.write(f"   {label}: {str(row[column]).replace(chr(10), ' ')}\n")
            output.write("\n")

    print(f"Predictions saved to {OUTPUT_FILE}")


if __name__ == "__main__":
    try:
        main()
    except Exception as error:
        # Append the error to the output file for easier debugging.
        with open(OUTPUT_FILE, "a", encoding="utf-8") as output:
            output.write(f"\nPrediction failed: {error}\n")
        print(f"Prediction failed: {error}", file=sys.stderr)
        sys.exit(1)
