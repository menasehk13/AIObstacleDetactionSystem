FROM tensorflow/tensorflow:latest

# Set the working directory
WORKDIR /app

# Copy the model files to the container
COPY model.tflite /app/model.tflite

# Copy the Python script to the container
COPY main.py /app/main.py

# Install any additional dependencies if required
# RUN apt-get update && apt-get install -y <package-name>

# Define the command to run when the container starts
CMD ["python", "main.py"]
