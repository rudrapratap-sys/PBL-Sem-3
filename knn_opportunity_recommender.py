import json
import pandas as pd
from sklearn.feature_extraction import DictVectorizer
from sklearn.neighbors import NearestNeighbors

DATASET_FILE = "opportunities_200.csv"
FEATURES_FILE = "opportunity_skill_features.csv"
OUTPUT_FILE = "top_10_predictions.txt"

df = pd.read_csv(DATASET_FILE)

def parse_skills(value):
    try:
        skills = json.loads(value)
        if not isinstance(skills, dict):
            return {}
        return {str(skill): float(level) for skill, level in skills.items()}
    except (json.JSONDecodeError, TypeError, ValueError):
        return {}

skill_dicts = df["required_skills"].apply(parse_skills)

# One numeric column per skill; each cell contains that opportunity's proficiency requirement.
vectorizer = DictVectorizer(sparse=False)
skill_matrix = vectorizer.fit_transform(skill_dicts)
skill_columns = vectorizer.get_feature_names_out()

features = pd.DataFrame(skill_matrix, columns=skill_columns)
features.insert(0, "opportunity_id", df["opportunity_id"].astype(str))
features.to_csv(FEATURES_FILE, index=False)

# Find nearest opportunities by comparing skill proficiency vectors.
knn = NearestNeighbors(n_neighbors=min(10, len(df)), metric="euclidean")
knn.fit(skill_matrix)

print("Enter your current skill levels, e.g. Python:7, pandas:5, numpy:6, docker:3")
user_input = input("Your skills: ").strip()

student_skills = {}
if user_input:
    for item in user_input.split(","):
        if ":" not in item:
            print(f"Skipping invalid item: {item}")
            continue
        name, level = item.split(":", 1)
        name = name.strip()
        try:
            score = float(level.strip())
            if name and 0 <= score <= 10:
                student_skills[name] = score
            else:
                print(f"Skipping invalid skill score: {item}")
        except ValueError:
            print(f"Skipping invalid skill score: {item}")

student_vector = vectorizer.transform([student_skills])
distances, indices = knn.kneighbors(student_vector)

with open(OUTPUT_FILE, "w", encoding="utf-8") as file:
    file.write("TOP 10 KNN OPPORTUNITY RECOMMENDATIONS\n")
    file.write("=" * 42 + "\n\n")
    for rank, (distance, index) in enumerate(zip(distances[0], indices[0]), start=1):
        row = df.iloc[index]
        file.write(f"{rank}. Opportunity ID: {row['opportunity_id']}\n")
        file.write(f"   Name: {row['name']}\n")
        file.write(f"   Category: {row['category']}\n")
        file.write(f"   Location: {row['location']}\n")
        file.write(f"   Skill distance: {distance:.3f}\n\n")

print(f"Saved expanded skill columns to: {FEATURES_FILE}")
print(f"Saved top 10 recommendations to: {OUTPUT_FILE}")
