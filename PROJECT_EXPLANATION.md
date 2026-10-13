# Project Explanation: Skill Gap Navigator + Opportunity Finder

## 1. Problem Statement

Students know some skills, but they are often confused about what skills are still
needed for a career role. They also miss useful opportunities because they do not
know which ones match their profile.

This project solves that problem using a simple C++ console application.

## 2. Objective

The objective is to:

- Store student login and profile details.
- Compare student skills with selected career role requirements.
- Show missing skills and readiness score.
- Suggest a simple learning roadmap.
- Find and rank suitable opportunities.

## 3. Why This Looks Like a First-Year Project

The project intentionally uses:

- Console menus.
- Simple text files instead of databases.
- Easy-to-read class names.
- Basic C++ STL data structures.
- Simple formulas that can be explained on a whiteboard.

## 4. OOP Concepts Used

### Class and Object

Classes used in the project:

- `User`
- `Student`
- `AuthSystem`
- `StudentManager`
- `SkillGapAnalyzer`
- `Opportunity`
- `OpportunityEngine`

Objects of these classes are created in `main.cpp`.

### Encapsulation

Class data members are private. Public getter and setter functions are used to
access or update them.

Example:

- `Student` keeps `cgpa`, `skills`, and `targetRole` private.
- `setCgpa()` validates that CGPA is between 0 and 10.

### Inheritance

`Student` inherits from `User`.

```cpp
class Student : public User
```

This means a student is also a user, but with extra details like branch, year,
CGPA, skills, interests, and target role.

### Abstraction

The main menu does not know how files are saved internally.

Examples:

- `AuthSystem` hides registration and login logic.
- `StudentManager` hides profile file handling.
- `SkillGapAnalyzer` hides skill comparison logic.
- `OpportunityEngine` hides ranking logic.

## 5. Data Structures Used

### Vector

Used to store:

- Users
- Student skills
- Interests
- Career roles
- Opportunities
- Matched and missing skills

### Unordered Set

Used for fast skill lookup while matching student skills with required skills.

Example:

If the student has `C++`, `OOP`, and `Git`, we store them in an unordered set so
checking whether `DSA` exists is faster.

### Unordered Map

Used for prerequisite relationships in the roadmap.

Example:

```text
C++ -> DSA
OOP -> DSA
JavaScript -> React
```

### Queue

Used in topological sorting to create the learning roadmap.

### Sorting

Used in `OpportunityEngine` to rank opportunities by relevance score.

## 6. Algorithms Used

### Skill Matching

The program compares required skills with student skills.

Time complexity:

```text
O(R + S)
```

Where:

- `R` = number of required skills
- `S` = number of student skills

### Readiness Score

Formula:

```text
Readiness Score = matched skills / required skills * 100
```

Example:

If 3 out of 5 skills match:

```text
3 / 5 * 100 = 60%
```

### Learning Roadmap

The project uses graph logic and topological sorting.

If a skill needs a prerequisite, the prerequisite comes first.

Example:

```text
JavaScript -> React
```

So the roadmap shows `JavaScript` before `React`.

Time complexity:

```text
O(V + E)
```

Where:

- `V` = number of skills
- `E` = number of prerequisite connections

### Opportunity Ranking

The program calculates a score:

- Skill match: 60 marks
- Domain match: 25 marks
- Preferred category match: 15 marks

Then it sorts opportunities from highest score to lowest score.

Time complexity:

```text
O(N log N)
```

Where `N` is the number of opportunities.

## 7. File Handling

The project uses text files:

| File | Purpose |
| --- | --- |
| `data/users.txt` | Stores registered users |
| `data/students.txt` | Stores student profile data |
| `data/roles.txt` | Stores target roles and required skills |
| `data/opportunities.txt` | Stores sample opportunities |

The files use simple `|` separated values.

## 8. Project Flow

```text
Start
  |
  |-- Register / Login
        |
        |-- Student Dashboard
              |
              |-- View Profile
              |-- Edit Profile
              |-- Add or Remove Skills
              |-- Select Target Role
              |-- Analyze Skill Gap
              |-- Discover Opportunities
              |-- Logout
```

## 9. Example Presentation Demo

Use this demo in front of teachers:

1. Start the program.
2. Register a new user.
3. Login using the same email and password.
4. Edit profile:
   - Branch: CSE
   - Year: 1
   - CGPA: 8.2
   - Interests: Coding, Software
5. Add skills:
   - C++
   - OOP
   - Git
6. Select target role:
   - Software Developer
7. Run skill gap analysis.
8. Explain that `DSA` and `SQL` are missing.
9. Show the roadmap.
10. Set preferred category as `Internship`.
11. Discover opportunities.
12. Explain that results are sorted using relevance score.

## 10. Team Member Explanation Split

For six members:

1. Authentication module: `User`, `AuthSystem`
2. Student profile module: `Student`, `StudentManager`
3. Skill gap module: `SkillGapAnalyzer`
4. Opportunity module: `Opportunity`, `OpportunityEngine`
5. File handling and data files
6. Testing, demo, and documentation

## 11. Known Limitations

- This is not a professional job recommendation system.
- The opportunity data is sample data.
- Password hashing is only for academic demonstration.
- The project uses text files, not a database.
- It does not use internet/live opportunity APIs.

## 12. Conclusion

This project demonstrates C++ OOP, file handling, STL data structures, searching,
sorting, and graph concepts through a useful student-focused application.
