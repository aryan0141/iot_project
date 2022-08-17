# Internet of Things

Used NodeJS to create some REST APIs to receive data from IoT Sensors

## Features
- Real Time Data Monitoring

## Tech

- [NodeJS] - For creating REST APIs!
- [MongoDB] - Database

## Procedure

- Navigate to the cloned repository.
    ```
    cd <project_directory_name>     #   iot_project
    ```
- Install all the dependencies.
    ```
    node install
    ```
- Install nodemon globally
    ```
    npm install nodemon -g
    ```
- Copy .env file
   ```
   cp .env.example .env
   ```
- Enter your MongoURI in the .env file

- Run development server on localhost
    ```
    nodemon server
    ```
- Access your webpage at localhost port 80
