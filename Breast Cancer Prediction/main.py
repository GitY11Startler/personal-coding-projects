from flask import Flask, request, render_template
import pandas as pd
import numpy as np
import pickle

# loading the model .pkl file, which is used to store Python objects in a binary format
model = pickle.load(open("C:\\Users\\DELL\\Downloads\\Breast Cancer Prediction\\model.pkl", "rb"))

# Flask app
app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/predict", methods=["POST"])
def predict():
    features = request.form['feature']
    features_list = features.split(",")
    np_features = np.asarray(features_list, dtype=np.float32)
    pred = model.predict(np_features.reshape(1, -1))

    output = ["Cancerous" if pred[0] == 0 else "Not Cancerous"]
    return render_template("index.html", message = output)


#python main
if __name__ == "__main__":
    app.run(debug=True)