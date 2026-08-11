# Parkinson's Freezing of Gait Syndrome Prediction

This repository contains code for predicting Freezing of Gait (FOG) episodes in patients with Parkinson's disease using machine learning techniques, specifically Logistic Regression and LightGBM models.

## Introduction

Parkinson's disease is a neurodegenerative disorder affecting movement. Freezing of Gait (FOG) is a debilitating symptom characterized by brief, involuntary gait arrests. This project aims to predict FOG episodes to facilitate timely interventions and improve patient quality of life.

## Dataset

**We have two major datasets here - tdcsfog and defog. Lets see the description and content of these datasets.**
**The tdcsfog folder includes** more than 800 csv files and accounts for **the majority of the information contained in the whole dataset for this competition**. Moreover, csv files in the edcsfog folder include annotation: StartHesitation, Turn, and Walking.

## Models

Two machine learning models are employed for prediction:

1. **Logistic Regression**: A simple yet effective classification algorithm modeling the probability of a binary outcome.
2. **LightGBM**: A gradient boosting framework known for its speed and efficiency in handling large datasets.

## Conclusion

It is possible that more features or more advanced machine learning algorithms could improve the accuracy of the models. Additionally, it may be useful to investigate other factors that contribute to the occurrence of freezing gait events, such as cognitive or environmental factors.

## Usage

To use the code in this repository:

1. Clone the repository:

   ```bash
   git clone https://github.com/tayalsaksham008/Parkinsons-FOG
