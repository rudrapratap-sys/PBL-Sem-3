
import json
import pickle
import numpy as np

MODEL_FILE = "knn_opportunity_model.pkl"
DATA_FILE = "filtered.json"

# 1. Load the trained model bundle
with open(MODEL_FILE, "rb") as file:
    bundle = pickle.load(file)

model = bundle["model"]
skill_columns = bundle["skill_columns"]
opportunity_ids = bundle["opportunity_ids"]
training_vectors = np.asarray(bundle["training_vectors"])

# 2. Load filtered JSON data
with open(DATA_FILE, "r", encoding="utf-8") as file:
    data = json.load(file)

student = data["student"]
opportunities = data["opportunities"]

if not opportunities:
    print("No opportunities passed the C++ filters.")
    raise SystemExit

# 3. Create student skill vector
student_skills = student.get("skills", {})

query = np.array([
    float(student_skills.get(skill, 0))
    for skill in skill_columns
], dtype=float)

query = np.clip(query, 0, 10).reshape(1, -1)

# 4. Map opportunity IDs to training vectors
id_to_index = {
    str(opp_id): i
    for i, opp_id in enumerate(opportunity_ids)
}

candidates = {}

for opportunity in opportunities:
    opp_id = str(opportunity.get("opportunity_id", ""))

    if opp_id in id_to_index:
        candidates[opp_id] = opportunity

if not candidates:
    print("No filtered opportunities matched the training dataset IDs.")
    raise SystemExit

# 5. Calculate distances for filtered opportunities
ranked = []

for opp_id, opportunity in candidates.items():
    index = id_to_index[opp_id]
    vector = training_vectors[index]

    distance = np.linalg.norm(query[0] - vector)
    ranked.append((distance, opportunity))

ranked.sort(key=lambda item: item[0])

# 6. Display top 5 opportunities
print("\nStudent:", student.get("name", "Unknown"))
print("\n===== TOP 5 OPPORTUNITIES =====")

for rank, (distance, opportunity) in enumerate(ranked[:5], start=1):
    print(f"\nRank: {rank}")
    print("ID:", opportunity.get("opportunity_id", "Unknown"))
    print("Name:", opportunity.get("name", "Unknown"))
    print("Category:", opportunity.get("category", "Unknown"))
    print("Location:", opportunity.get("location", "Unknown"))
    print(f"Skill distance: {distance:.2f}")
