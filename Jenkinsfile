pipeline {
    agent any
    stages {
        stage('Clone Repository') {
            steps {
                git 'https://github.com/your-username/your-repo.git'
            }
        }
        stage('Build') {
            steps {
                sh 'mvn clean package'
            }
        }
        stage('Build Docker Image') {
            steps {
                sh 'docker build -t your-app .'
            }
        }
        stage('Run Container') {
            steps {
                sh 'docker run -d -p 8080:8080 your-app'
            }
        }
    }
}
