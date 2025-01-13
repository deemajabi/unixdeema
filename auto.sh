#!/bin/bash

GIT_REPO_PATH="https://github.com/deemajabi/unixdeema"
DEPLOYMENT_DIR="/path/to/deployment/directory"
CONTAINER_NAME="your_container_name"
IMAGE_NAME="your_image_name"
GIT_BRANCH="main"

cd $GIT_REPO_PATH || { echo "Git repository path not found"; exit 1; }

git checkout $GIT_BRANCH
git pull origin $GIT_BRANCH || { echo "Failed to pull from Git repository"; exit 1; }

echo "Running tests..."

docker stop $CONTAINER_NAME
docker rm $CONTAINER_NAME

docker build -t $IMAGE_NAME $DEPLOYMENT_DIR || { echo "Failed to build Docker image"; exit 1; }

docker run -d --name $CONTAINER_NAME $IMAGE_NAME || { echo "Failed to run Docker container"; exit 1; }

docker system prune -f

echo "Deployment completed successfully!"
