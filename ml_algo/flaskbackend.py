from flask import Flask
import pickle
import numpy as np
import pandas as pd
app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello, World!'

# get variables from url

model = pickle.load(open('model.pkl', 'rb'))


# to_predict = np.array([[2, 9, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0]])
import numpy as np
def encode_string_to_int(string):
    encoded_int = [ord(char) for char in string]
    return encoded_int

import pandas as pd


@app.route('/hello/<age>/<gender>/<disease>/<liquid>')
def hello(age, drip_rate, gender, disease, liquid):
#   print the variables
    to_predict = np.array([[2, 9, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0]])
    return (str(model.predict(to_predict)))




# sample url http://localhost:5000/hello/2/1/1/1


