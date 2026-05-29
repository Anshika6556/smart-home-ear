# 🚨 Smart Home Ear

An AI-powered audio surveillance and emergency response system designed to detect distress and danger-related sounds in real time and automatically trigger alerts for enhanced public safety.

## 🎯 Problem Statement

Many dangerous situations in locations such as roads near girls' hostels, public washrooms, private cabins, parking areas, and old-age homes go unnoticed due to the absence of continuous monitoring. Smart Home Ear aims to provide an intelligent safety layer by analyzing environmental sounds and generating real-time alerts when potential threats are detected.

---

## ✨ Features

* Real-time audio threat detection
* AI-powered sound classification
* Automated emergency alerts
* Live CCTV integration
* Event logging and monitoring
* SOS functionality
* Guardian and emergency contact notifications
* Interactive monitoring dashboard
* WhatsApp and SMS Alert Integration
* Live Camera-Based Threat Detection

---


## 📊 Dataset

The model was trained on:

* UrbanSound8K Dataset
* ESC-50
* Additional public environmental audio dataset
* Custom merged and cleaned dataset

### Dataset Scale

* 18,000+ audio samples and Mel-Spectrograms
* Multi-class audio categorization
* Danger, Alert, and Safe sound classes

---

## 🔧 Data Processing Pipeline

### Data Cleaning

* Removed corrupted audio files
* Standardized sampling rates
* Eliminated duplicate samples
* Balanced class distributions

### Feature Engineering

* Mel-Spectrogram Generation
* Audio normalization
* Spectrogram resizing and padding
* Log-scaled frequency representation

### Preprocessing

* Noise handling
* Fixed audio duration processing
* Feature scaling
* Data validation and quality checks

---

## 🧠 Model Development

### Architecture

* Convolutional Neural Network (CNN)
* TensorFlow / Keras

### Workflow

Audio Input
→ Preprocessing
→ Mel-Spectrogram Generation
→ CNN Classification
→ Risk Assessment
→ Alert Generation

### Performance

| Metric              | Score    |
| ------------------- | -------- |
| Accuracy            | 95%      |
| Recall              | 94%      |
| Precision           | 95%+     |
| False Positive Rate | Very Low |

---

## ⚙️ Tech Stack

### AI / Machine Learning

* Python
* TensorFlow
* Keras
* Librosa
* NumPy

### Backend

* FastAPI
* REST APIs

### Frontend

* React.js
* Streamlit(older ui framework)
* Tailwind CSS

### Data Processing

* Mel-Spectrogram Feature Engineering
* Audio Signal Processing

---

## 🏗️ System Architecture

Audio Stream
↓
Preprocessing
↓
Mel-Spectrogram Conversion
↓
CNN Model
↓
Danger Prediction
↓
FastAPI Backend
↓
Streamlit Dashboard
↓
Alerts & Notifications

---

## 📱 Use Cases

* Girls' Hostel Safety\
* Smart Homes
* Public Washrooms
* Private Cabins
* Parking Areas
* Elderly Care Monitoring
* Smart Surveillance Systems
* Emergency Response Systems

---

## 🚀 Future Enhancement

* Mobile Application Integration
* Real-Time Cloud Deployment
* Multi-Language Distress Detection
* Edge AI Deployment


