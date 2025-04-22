pipeline {
    agent any

    environment {
        IMAGE_NAME = 'banking-system-app'
        CONTAINER_NAME = 'banking-container'
    }

    stages {
        stage('Checkout') {
            steps {
                // Replace with your actual GitHub repo URL
                git 'https://github.com/vinav514/banking-system.git'
            }
        }

        stage('Build Docker Image') {
            steps {
                script {
                    bat 'docker build -t ${IMAGE_NAME} .'
                }
            }
        }

        stage('Run Docker Container') {
            steps {
                script {
                    bat '''
                    docker stop ${CONTAINER_NAME} || true
                    docker rm ${CONTAINER_NAME} || true
                    docker run -d --name ${CONTAINER_NAME} ${IMAGE_NAME}
                    '''
                }
            }
        }

        stage('Post Build Cleanup') {
            steps {
                echo 'Build complete. Docker container is running.'
            }
        }
    }

    post {
        success {
            echo '✅ Pipeline completed successfully!'
        }
        failure {
            echo '❌ Pipeline failed!'
        }
    }
}
