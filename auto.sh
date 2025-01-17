#!/bin/bash

# Step 4: Update Application Code
echo "Updating application code..."
git pull origin main

# Step 5: Compile and Test Code
echo "Compiling code..."
# Add your compile command here (e.g., make or PHP test commands)

# Step 6: Build and Deploy Container
echo "Building Docker image..."
docker build -t unixdeema:latest .

echo "Stopping and removing old container..."
docker stop unixdeema || true
docker rm unixdeema || true

echo "Deploying new container..."
docker run -d -p 8080:80 --name unixdeema unixdeema:latest

echo "Deployment complete. Application running on http://localhost:8080."
