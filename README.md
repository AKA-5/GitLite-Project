# GitLite - A Lightweight Version Control System  

GitLite is a simplified yet powerful version control system designed to efficiently handle file versioning using tree structures. Unlike traditional methods, GitLite minimizes data redundancy, optimizes performance for large files, and ensures data integrity through cryptographic hashing.  

---

##  Features  
✔️ **Initialize Repository**: Choose between AVL Tree, B-Tree, or Red-Black Tree for organizing CSV data.  
✔️ **Commit Changes**: Save versions with meaningful messages.  
✔️ **Branching & Checkout**: Work on different versions independently.  
✔️ **Log & History**: View commit history for any branch.  
✔️ **Merge Branches**: Combine changes seamlessly.  
✔️ **Data Integrity & Security**: Uses **SHA-256** hashing and **Merkle Trees** for corruption detection.  

---

## 📂 Installation & Setup  

### 🛠 Prerequisites  
- **Microsoft Visual Studio** (Recommended)  
- **OpenSSL Library** (For SHA-256 hashing)  

### 🔧 Setting up OpenSSL  
1. Install OpenSSL: [YouTube Guide](https://www.youtube.com/watch?v=u8E6YXZkE-A)  
2. Add OpenSSL paths in Visual Studio:  
   - **Include Directories**: `C:\path\to\openssl\include`  
   - **Library Directories**: `C:\path\to\openssl\lib`  
   - **Dependencies**:  
     ```
     libssl.lib
     libcrypto.lib
     ```
   - **Environment Variable**: Add `C:\openssl-3.4.0\build\bin` to `PATH`.  

---

## 🛠 Usage Guide  

GitLite provides an interactive command-line interface with various commands for version control. Below is a breakdown of the available commands and their usage.

### 📌 Initializing a Repository  
```bash
> init
Description: Initializes a new repository.
Input: Prompts for a CSV file and repository name.
Example:
> init
Input the name of the file with extension: data.csv
Enter Repository Name: my_project
```
###  Branch Management
```bash
> branch <branch_name>
Description: Creates a new branch from the current repository state.
Example:
> branch feature-1

> checkout <branch_name>
Description: Switches to an existing branch.
Example:
> checkout feature-1

> branches
Description: Displays a list of all branches.

> delete-branch <branch_name>
Description: Deletes the specified branch.
Example:
> delete-branch feature-1

> current-branch
Description: Displays the name of the branch you are currently working on.
```
### 🔄 Saving & Loading Repositories
```bash
> save
Description: Saves the current state of the repository for persistence.

> load <repository_name>
Description: Loads a previously saved repository.
Example:
> load my_project

> delete <repository_name>
Description: Deletes the specified repository.
Example:
> delete my_project
```
###  Committing & Logging
```bash
> commit
Description: Further provides you with options to add, edit or delete data and saves the current changes in the repository.

> log
Description: Displays the commit log history.
```
### 🔀 Merging & Tree Visualization
```bash
> merge <source_branch> <target_branch>
Description: Merges changes from one branch into another.
Example:
> merge feature-1 main

> visualize-tree <branch_name>
Description: Displays the tree structure for the specified branch.
Example:
> visualize-tree main
```

### ⚙️ Miscellaneous Commands
```bash
> commands
Description: Displays a list of all available commands to navigate in GitLite.

> cls
Description: Clears the command-line screen.

> exit
Description: Exits the program and prompts whether to save changes.
Example:
> exit
Do you want to save the changes? (Y/N): Y
Changes saved.
```

🚧 Unimplemented Features
The following features are not yet implemented but may be added in future updates:
B-Tree Support: Currently, only AVL Trees and Red-Black Trees are fully implemented.
Tree Visualization: The visualize-tree command is not yet functional but is planned for future releases.

## 🛠 Implementation Guide
How We Implemented GitLite

### Tree Structures:
- We implemented AVL Trees and Red-Black Trees to organize and manage the CSV data efficiently.
- Each node in the tree represents a file or directory, and the tree structure ensures fast search, insertion, and deletion operations.

### Version Control:
- The commit command saves the current state of the repository, creating a new version with a unique identifier and commit message.
- The log command displays the commit history, allowing users to track changes over time.

### Branching:
- The branch command creates a new branch, which is stored in a separate folder.
- The checkout command allows users to switch between branches, enabling parallel development.

### Merging:
- The merge command combines changes from one branch into another, ensuring seamless integration of updates.

### Data Integrity:
- We used SHA-256 hashing and Merkle Trees to ensure data integrity and detect corruption.
- Each node in the tree has a cryptographic hash, and changes propagate up the tree, making it easy to identify corrupted data.

### File Storage:
- Instead of loading the entire tree into memory, each node is stored in a separate file, optimizing performance for large datasets.
##  Credits 🤝
This project was developed by **Muhammad Kaleem Akhtar**, **Obaidullah Shoaib**, and **Fatik Bin Imran** as part of the Data Structures course. Special thanks to our professor and mentor for their guidance and support.
