# CNT_Lab_exam


Experiment No. 1:

1a) [Wired Network](https://drive.google.com/file/d/1hupU9eNcRHqXHDiaw0wmL8EaYlUl0VVz/view?usp=sharing)

1b) [Hands On Networking Commands](https://drive.google.com/file/d/15v7gbXNY-Eri2ZXm0VHrpc8SKVmG0ATt/view?usp=sharing)


Experiment NO. 5:

README.md:
```
# Student Result Management System

A full-stack application for managing student semester results using Java Spring Boot (Backend) and React + Vite (Frontend).

## 🚀 Features

1) Responsive Frontend: Built with React and Tailwind CSS.

2) Result Calculation: Automatically computes totals, percentages, and grades (Distinction, First Class, etc.).

3) Persistent Storage: Stores student records in a MySQL database.

4) Demo Mode: Frontend includes a toggle to simulate data without a running backend for UI testing.

5) REST API: Spring Boot backend provides endpoints for adding and retrieving results.

## 🛠️ Tech Stack

1) Frontend: React (Vite), Tailwind CSS, Lucide React (Icons).

2) Backend: Java Spring Boot (Web, Data JPA), Hibernate.

3) Database: MySQL.

4) Tools: Maven, Node.js, npm.

## 📋 Prerequisites

Ensure you have the following installed:
1) Java JDK 17+
2) Node.js & npm
3) MySQL Server (Running on port 3306)

## ⚙️ Setup & Installation

1. Database Setup (MySQL)
You do not need to run SQL scripts manually. The application handles table creation automatically.

- Open your MySQL Workbench or Client.

- Ensure your MySQL service is running.

- (Optional but recommended) Create a database named student_results_db. If skipped, the app config is set to create it automatically.

2. Backend Setup (Spring Boot)

- Navigate to the `backend` folder:
```bash
cd backend
```

- Open `src/main/resources/application.properties`.

- Update the `password` to match your local MySQL root password:

```
spring.datasource.username=root
spring.datasource.password=YOUR_MYSQL_PASSWORD_HERE
```

- Important: Ensure CORS is allowed for the frontend port. Open `ResultController.java` and confirm this line exists:
```java
@CrossOrigin(origins = "http://localhost:5173")
```

- Run the application:
```bash
./mvnw spring-boot:run
```

The backend will start on `http://localhost:8080`.

3. Frontend Setup (React)

- Open a new terminal and navigate to the student-results-frontend folder:
```bash
cd student-results-frontend
```

- Install dependencies:
```bash
npm install
```

(Note: Ensure you installed the stable Tailwind version as discussed: `npm install -D tailwindcss@3.4.17 postcss autoprefixer`)

- Start the development server:
```bash
npm run dev
```
The frontend will start on `http://localhost:5173`.

## 🖥️ Usage

1) Open your browser to http://localhost:5173.

2) Toggle Connection:
- By default, the app starts in "Frontend Demo Mode" (Yellow badge). This uses simulated data.

- Click the toggle switch in the top right corner. It should turn Green and say "Connected to Backend".

3) Enter Data:

- Fill in Student Name, Roll No, and marks for the 4 subjects.

- Marks are validated (MSE <= 30, ESE <= 70).

4) Save: Click "Save Result". The data will be sent to the MySQL database and displayed in the table on the right.

## 🔗 API Endpoints

Base URL: `http://localhost:8080/api/results`

Method

Endpoint

Description

Payload

GET

/

Fetch all results

-

POST

/add

Add a new result

JSON Object (Student Data)

❓ Troubleshooting

"Connection Refused" (Backend):

Check if MySQL service is running.

Verify the password in application.properties.

"CORS Error" / Fetch Failed (Frontend):

Ensure the backend is running.

Ensure ResultController.java allows http://localhost:5173.

Restart the backend after making Java changes.

Tailwind styles missing:

Ensure tailwind.config.js exists and content array points to ./src/**/*.{js,ts,jsx,tsx}.

Ensure src/index.css contains the @tailwind directives.
```
