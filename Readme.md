# Skill Gap Navigator + Opportunity Finder

This is a simple C++ console project made for a first-year BTech PBL presentation.
It helps a student compare their skills with a target career role and then finds
basic opportunities like internships, workshops, hackathons, and scholarships.

## Features

- Register and login using email and password.
- Save student profile data in text files.
- Add or remove skills.
- Select a target role.
- Show matched skills, missing skills, readiness score, and learning roadmap.
- Rank opportunities using CGPA, skill match, target role, and category preference.

## Folder Structure

```text
PBL/
├── include/
│   ├── AuthSystem.h
│   ├── Opportunity.h
│   ├── OpportunityEngine.h
│   ├── SkillGapAnalyzer.h
│   ├── Student.h
│   ├── StudentManager.h
│   ├── User.h
│   └── Utils.h
├── src/
│   ├── AuthSystem.cpp
│   ├── Opportunity.cpp
│   ├── OpportunityEngine.cpp
│   ├── SkillGapAnalyzer.cpp
│   ├── Student.cpp
│   ├── StudentManager.cpp
│   ├── User.cpp
│   ├── Utils.cpp
│   └── main.cpp
├── data/
│   ├── opportunities.txt
│   └── roles.txt
├── PROJECT_EXPLANATION.md
└── README.md
```

## Compile

Run this command from the project folder:

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/User.cpp src/Student.cpp src/AuthSystem.cpp src/StudentManager.cpp src/Utils.cpp src/SkillGapAnalyzer.cpp src/OpportunityEngine.cpp -o skill_gap_navigator.exe
```

## Run

```bash
./skill_gap_navigator.exe
```

On Windows PowerShell:

```powershell
.\skill_gap_navigator.exe
```

## Data Files

- `data/users.txt`: created automatically after registration.
- `data/students.txt`: created automatically for saved student profiles.
- `data/roles.txt`: sample role and skill requirement data.
- `opportunities_200.csv`: sample opportunity data used by the opportunity filter.
- `filtered.json`: generated for the Python opportunity recommender.

The project uses simple `|` separated text files to keep the code easy to explain.

## Main Classes

- `User`: stores account details.
- `Student`: inherits from `User` and stores branch, CGPA, skills, interests, and target role.
- `AuthSystem`: handles registration, login, duplicate email checking, and user file saving.
- `StudentManager`: loads and saves student profiles.
- `SkillGapAnalyzer`: compares student skills with role skills and creates a roadmap.
- `Opportunity`: stores one opportunity.
- `OpportunityEngine`: ranks opportunities based on profile match.

## Demo Flow

1. Register a new student account.
2. Login with the same email and password.
3. Edit basic details and add CGPA.
4. Add skills like `C++`, `OOP`, and `Git`.
5. Select `Software Developer` as the target role.
6. Run skill gap analysis.
7. Set preferred category as `Internship`.
8. Discover ranked opportunities.

## Limitations

- Password storage is only for academic demo use.
- Text files use simple separators, so avoid typing `|` inside names or fields.
- Opportunity data is sample data, not real-time verified opportunity data.
