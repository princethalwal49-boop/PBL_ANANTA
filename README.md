# PeerLearn File-Based

**Project status: Approximately 60% complete**

PeerLearn File-Based is a beginner-friendly, console-based C++ project designed to support peer learning and student collaboration. It uses core data structures and text-file storage to keep the implementation approachable for students learning C++.

## Basic Details

- **Language:** C++ (C++11)
- **Interface:** Console-based
- **Storage:** Text files
- **Current progress:** About 60% of the code has been completed
- **Build approach:** Compile the project source files together using `g++`

## Planned and Implemented Components

The project is structured around these components:

- **Fixed arrays:** Store simple collections of data.
- **Linked lists:** Manage data using linked-list structures.
- **Skill tree:** Represent skills and their relationships in a simple tree.
- **Student graph:** Model connections between students.
- **Matching:** Support matching students based on relevant information.
- **Request queue:** Organize incoming requests.
- **Ratings:** Handle rating-related functionality.
- **Admin module:** Provide basic administrative operations.
- **File storage:** Read and write project data using text files.

> **Progress note:** The project is approximately 60% complete. Some modules or workflows may still be under development, testing, or integration. The exact completion status can change as implementation continues.

## Build

Make sure a C++ compiler such as `g++` is installed and available in your terminal. From the directory containing the source files, run:

```bash
g++ -std=c++11 main.cpp Student.cpp FileStorage.cpp RequestQueue.cpp Rating.cpp Admin.cpp SkillTree.cpp Graph.cpp Matching.cpp -o PeerLearnFileBased
```

On Windows, run the generated executable with:

```powershell
.\PeerLearnFileBased.exe
```

On Linux or macOS, run:

```bash
./PeerLearnFileBased
```

## Running the Program

1. Open a terminal in the project directory.
2. Compile the source files using the command above.
3. Run the generated executable.
4. Follow the console menu prompts and enter the requested number or text.

## Notes

- The program uses direct `cin` and `cout` input/output in `main.cpp`.
- The current input flow is intended to stay simple and beginner-friendly.
- This README describes the project structure and current reported progress; it does not claim that every listed feature is fully finished.

## Next Steps

- Complete the remaining approximately 40% of the implementation.
- Test each module and its interactions.
- Verify text-file reading and writing.
- Test the complete menu flow and fix any bugs.
- Update this README as features are completed.
