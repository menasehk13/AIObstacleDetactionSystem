import numpy as np
import tensorflow as tf
from tensorflow import keras
from keras import layers
from keras.preprocessing.image import ImageDataGenerator
from PIL import Image
import scipy
# image height and width
img_height, img_width = 224, 224
# Set the paths to your training and validation image directories
train_dir = './dataset/train'
val_dir = './dataset/validation'
train_datagen = ImageDataGenerator(
    rescale=1./255,
)

# Set up normalization for validation images 
val_datagen = ImageDataGenerator(rescale=1./255)

# Flow the images from the directories using the data generators
train_generator = train_datagen.flow_from_directory(
    train_dir,
    target_size=(img_height, img_width),
    batch_size=32,
    class_mode='binary'
)

val_generator = val_datagen.flow_from_directory(
    val_dir,
    target_size=(img_height, img_width),
    batch_size=32,
    class_mode='binary'
)

# Use the generators to load the images and labels
train_images, train_labels = next(train_generator)
val_images, val_labels = next(val_generator)

# Define the neural network model
model = keras.Sequential([
    layers.Conv2D(16, 3, activation='relu', input_shape=(img_height, img_width, 3)),
    layers.MaxPooling2D(),
    layers.Dropout(0.5),
    layers.Conv2D(32, 3, activation='relu'),
    layers.MaxPooling2D(),
    layers.Dropout(0.5),
    layers.Conv2D(64, 3, activation='relu'),
    layers.MaxPooling2D(),
    layers.Dropout(0.5),
    layers.Flatten(),
    layers.Dense(128, activation='relu'),
    layers.Dense(1, activation='sigmoid')
])

# Compile the model
model.compile(optimizer='adam',
              loss='binary_crossentropy',
              metrics=['accuracy'])

model.summary()

# Train the model
history = model.fit(train_images, train_labels, epochs=10, validation_data=(val_images, val_labels))

# Convert the model to TensorFlow Lite format
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# Save the TensorFlow Lite model
# comment this code or it will build the model before training
with open('model.tflite', 'wb') as f:
    f.write(tflite_model)
