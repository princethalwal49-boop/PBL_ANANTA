# PeerLearn — File-Based Peer Learning Platform

PeerLearn is a console-based C++ application that helps students find suitable peers to learn from, manage learning requests, rate completed sessions, and administer the platform. It is designed as a data-structures project: fixed arrays, linked lists, a tree, an undirected graph, a hash index, and text-file persistence are all used deliberately.

## Features

- Student registration and login with unique student IDs and usernames.
- Student profiles showing branch, semester, teachable skills, and rating.
- Fast teacher recommendations for a requested skill.
- Learning requests that can be accepted or rejected by the receiving student.
- Peer ratings, permitted only after an accepted learning request has created a graph connection between the two students.
- Peer reporting for connected learning partners, with an administrator review and ban option.
- Automatic flagging and banning for consistently poor ratings; administrators can also ban or unban manually.
- Administrator views for students, requests, and ratings, plus student removal.
- A hierarchical skill tree for browsing the supported learning areas.
- A student connection graph, including connections created by accepted learning requests.
- Persistent student, request, rating, and graph connection data.
- Seeded demo data that demonstrates all major workflows immediately.

## Data structures used

- **Array**: stores up to 100 students.
- **Linked queue**: stores learning requests in submission order.
- **Linked list**: stores rating records.
- **General tree**: stores the skill hierarchy using child/sibling links.
- **Undirected adjacency-list graph**: stores student connections.
- **Hash index**: maps normalized skills directly to students who teach them.

## Fast matching algorithm

The matcher does not scan every student for every search. It creates a cached hash index when the student list changes (loaded, registered, or removed). Skills are normalized to lower case and comma-separated entries such as `C++, Python` are indexed separately.

For a query, the requested skill is hashed directly to the relevant candidate chain. Only those candidates are scored and ranked. Average lookup cost is **O(1 + k)**, where `k` is the number of teachers for that skill. Rebuilding the index costs **O(t)** only after student data changes, where `t` is the total number of entered skills.

Recommendations use rating, branch similarity, and semester proximity. Banned accounts are never recommended.

## Demo credentials

Student account:

```text
Username: aarav
Password: pass123
```

Administrator account:

```text
Username: admin
Password: admin123
```

The demo contains ten students, accepted/rejected/pending requests, ratings, and graph relationships. Search for `Python` while logged in as Aarav to see the ranked matching flow.

## Build and run

From the project directory, compile with a C++11-compatible compiler:

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp Student.cpp FileStorage.cpp RequestQueue.cpp Rating.cpp Report.cpp Admin.cpp SkillTree.cpp Graph.cpp Matching.cpp -o PeerLearnFileBased.exe
.\PeerLearnFileBased.exe
```

## Persistent files

- `students.txt` — profile, account, skill, and manual-ban data.
- `requests.txt` — learning requests and their statuses.
- `ratings.txt` — peer rating records.
- `connections.txt` — graph connections, created after graph data is saved.
- `reports.txt` — peer reports submitted for administrator review.

All records use `|` as the separator, so user text cannot contain that character.

## Rating safety policy

Students receive a visible warning after at least two ratings with an average of `2.5/5` or lower. They are automatically banned after at least four ratings with an average of `1.5/5` or lower. Administrators may ban or unban accounts manually, including after reviewing peer reports.

## Typical workflow

1. Log in with a demo student account.
2. Open **Get matches** and request a skill such as `Python` or `C++`.
3. Send a request to a recommended teacher.
4. Log in as the receiving student and accept or reject it.
5. After acceptance, either participant can rate the other once.
6. Log in as the administrator to inspect data and manage accounts.
