pipeline {
    agent any

    stages {
        stage('Clone Repository') {
            steps {
                sh 'rm -rf unixdeema'
                git url: 'https://github.com/deemajabi/unixdeema.git'
            }
        }
       
        stage('Clean') {
            steps {
                sh 'cd unixdeema'
                sh 'docker compose down'
            }
        }
        stage('Run Container') {
            steps {
                sh 'cd unixdeema'
                sh 'docker compose up -d'
            }
        }
    }
}
