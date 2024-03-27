import numpy as np


class Dataframe:
    def __init__(self, data):
        """
        A dataframe holds a 2 dimensional heterogeneous data.


        Args:
            data (dic): 
                A dictionary of strings mapped to NumPy arrays. The key will
                become the column name.
        """
