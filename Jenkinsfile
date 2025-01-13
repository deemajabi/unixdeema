pipeline {
    agent any
    environment {
        REPO_URL = 'https://github.com/deemajabi/unixdeema.git'
        IMAGE_NAME = 'unixdeema-app'
        CONTAINER_NAME = 'unixdeema-container'
    }
    stages {
        stage('Clone Repository') {
            steps {
                git "${REPO_URL}"
            }
        }
        stage('Build') {
            steps {
                sh 'mvn clean package'
            }
        }
        stage('Build Docker Image') {
            steps {
                sh 'docker build -t ${IMAGE_NAME} .'
            }
        }
        stage('Run Container') {
            steps {
                sh 'docker run -d -p 8080:8080 --name ${CONTAINER_NAME} ${IMAGE_NAME}'
            }
        }
    }
}
