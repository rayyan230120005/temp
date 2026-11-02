
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score, confusion_matrix

# Read dataset
df = pd.read_csv("emails.csv")

# Remove email ID column
X = df.drop(['Email No.', 'spam'], axis=1)
y = df['spam']

# Split dataset
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

# Normalize features
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# KNN Classification
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train, y_train)
pred1 = knn.predict(X_test)

# SVM Classification
svm = SVC(kernel='linear')
svm.fit(X_train, y_train)
pred2 = svm.predict(X_test)

# Evaluate models
for name, pred in [("KNN", pred1), ("SVM", pred2)]:
    print("\n", name)
    print("Accuracy:", accuracy_score(y_test, pred))
    print("Confusion Matrix:\n", confusion_matrix(y_test, pred))
