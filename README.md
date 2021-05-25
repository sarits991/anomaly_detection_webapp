# Anomaly Detection Web App

A restful api and web client for anomaly detection

## Getting Started
The following instructions will guide you how to install Node.js and run the web application.
* [Download and install Node.js](https://nodejs.org/en/download/)
* Clone this project:
    ```bash
       git clone https://github.com/sarits991/anomaly_detection_webapp.git
   ```
* Run `npm install` command in the root project to install all required dependencies.
* Run `npm start` command in the root project to start the local server in port 8080.

## Operating Instructions for Rest Api
* **URL:** `http://localhost:8080/detect`
* **Method:** `POST`
* **Body Params:**
  * **model_type:** type of the algorithm to detect anomalies (hybrid/regression).
  * **train_file:** upload csv file to learn anomalies.
  * **detect_file:** upload csv file to detect anomalies.
* **Success Response:**
  * **Code:** 200
  * **Content:**
    ```json
    [{
    "feature1": "name of feature 1",
    "feature2": "name of feature 2",
    "range": ["range of timestamp"]
    }]
    ```
* **Error Response:**
  * **Code:** 400
  * **Content:**
    ```json
    {
    "error" : "invalid data/invalid model type/invalid files"
    }
    ```

## Operating Instructions for Web client
* Load `http://localhost:8080` page.
* Choose algorithm to dete* Load `http://localhost:8080` page.
* Choose algorithm to detect anomalies in the scroll list.
* Upload train csv file.
* Upload detect csv file.ct anomalies in the scroll list.
* Upload train csv file.
* Upload detect csv file.
* Click on the upload button to detect anomalies.
* Output:
  * "**pending...** " message while the anomalies are calculated.
  * **Success Response:** report list of the anomalies
     ``` 
       feature1 : "name of feature 1",
       feature2 : "name of feature 2",
       range: ["range of timestamp"]
     ```
  * **Error Response:** error message
    ```
    invalid data/invalid model type/invalid files
    ```

## Project Structure
The project architecture is based on MVC design pattern.Therefore, the project divide into three main parts:
* **View:** used for all the UI logic of the application. The view get the html page and the response data from the controller, processing and display it.
* **Controller:** serves as a link between the view and model. the controller process the incoming requests,
  manipulate data using the Model component, and send the data to the View component.
* **Model:** holds the logic buisness, includes the c++ addon.

According to Node.js architecture the project consist Route component in order to forward the incoming requests to the appropriate controller functions.

# Class Diagram

The class diagram has three layers according to MVC architecture : Model, Controller, View

![ClassDiagram](https://github.com/sarits991/anomaly_detection_webapp/tree/develop/webapp_uml.png)