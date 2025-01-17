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
                script {
                    if (fileExists('unixdeema/docker-compose.yml')) {
                        sh 'cd unixdeema ; docker compose down'
                    } else {
                        echo 'docker-compose.yml not found, skipping docker compose down'
                    }
                }
            }
        }
        
        stage('Run Container') {
            steps {
                script {
                    if (fileExists('unixdeema/docker-compose.yml')) {
                        sh 'cd unixdeema ; docker compose up -d'
                    } else {
                        echo 'docker-compose.yml not found, skipping docker compose up'
                    }
                }
            }
        }
    }
}
