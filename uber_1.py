
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import r2_score, mean_squared_error

# Read dataset
df = pd.read_csv("uber.csv")

# Preprocessing
df = df.dropna()
df = df.drop(['Unnamed: 0', 'key'], axis=1, errors='ignore')

# Convert datetime into numerical features
df['pickup_datetime'] = pd.to_datetime(df['pickup_datetime'])
df['hour'] = df['pickup_datetime'].dt.hour
df['day'] = df['pickup_datetime'].dt.day
df = df.drop('pickup_datetime', axis=1)

# Identify and remove fare outliers using IQR
Q1 = df['fare_amount'].quantile(0.25)
Q3 = df['fare_amount'].quantile(0.75)
IQR = Q3 - Q1
df = df[(df['fare_amount'] >= Q1 - 1.5*IQR) &
        (df['fare_amount'] <= Q3 + 1.5*IQR)]

# Check correlation
print(df.corr())

# Split features and target
X = df.drop('fare_amount', axis=1)
y = df['fare_amount']

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# Linear Regression
lr = LinearRegression()
lr.fit(X_train, y_train)
pred1 = lr.predict(X_test)

# Random Forest Regression
rf = RandomForestRegressor(n_estimators=10, random_state=42)
rf.fit(X_train, y_train)
pred2 = rf.predict(X_test)

# Evaluation
for name, pred in [("Linear Regression", pred1),
                   ("Random Forest", pred2)]:
    print("\n", name)
    print("R2:", r2_score(y_test, pred))
    print("RMSE:", np.sqrt(mean_squared_error(y_test, pred)))
