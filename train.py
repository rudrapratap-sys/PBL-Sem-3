import os
import pickle
import pandas as pd
from sklearn.neighbors import NearestNeighbors

# Dataset must contain one row per opportunity, an opportunity_id column,
# and one numeric column per skill.
DATASET_CANDIDATES = [
    "knn_opportunity_dataset.csv",
    "opportunity_skill_features.csv",
]
MODEL_FILE = "model.pkl"


def find_dataset():
    for filename in DATASET_CANDIDATES:
        if os.path.exists(filename):
            return filename
    raise FileNotFoundError(
        "Dataset not found. Put knn_opportunity_dataset.csv or "
        "opportunity_skill_features.csv in the same folder as train.py."
    )


def main():
    dataset_file = find_dataset()
    df = pd.read_csv(dataset_file)

    if "opportunity_id" not in df.columns:
        raise ValueError("Dataset must contain an 'opportunity_id' column.")

    skill_columns = [c for c in df.columns if c != "opportunity_id"]
    if not skill_columns:
        raise ValueError("Dataset has no skill columns.")

    # Keep only numeric skill columns and replace blank values with zero.
    X = df[skill_columns].apply(pd.to_numeric, errors="coerce").fillna(0)
    X = X.clip(lower=0, upper=10)

    # NearestNeighbors is suitable because we want the 15 closest opportunities,
    # not one predicted class label.
    model = NearestNeighbors(
        n_neighbors=min(15, len(df)),
        metric="euclidean",
        algorithm="auto"
    )
    model.fit(X.to_numpy())

    # One pickle file stores everything prediction.py needs:
    # trained model, skill column order, opportunity IDs and training vectors.
    bundle = {
        "model": model,
        "skill_columns": skill_columns,
        "opportunity_ids": df["opportunity_id"].astype(str).tolist(),
        "training_vectors": X.to_numpy(),
        "dataset_file": dataset_file,
    }

    with open(MODEL_FILE, "wb") as file:
        pickle.dump(bundle, file)

    print(f"Training complete using: {dataset_file}")
    print(f"Opportunities: {len(df)}")
    print(f"Skill columns: {len(skill_columns)}")
    print(f"Saved model: {MODEL_FILE}")


if __name__ == "__main__":
    main()
