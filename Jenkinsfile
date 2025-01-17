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
                sh'''
                cd unixdeema
                ls -l
                docker compose down
                '''
            }
        }
        stage('Run Container') {
            steps {
                sh'''
                cd unixdeema
                docker compose up -d
                '''
            }
        }
    }
}
