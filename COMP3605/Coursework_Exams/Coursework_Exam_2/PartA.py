#Christopher Sahadeo
#816000772


import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import KFold
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score, precision_score, f1_score, confusion_matrix, classification_report
import numpy as np
from sklearn.preprocessing import normalize
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
from sklearn.neighbors import KNeighborsClassifier


#1.1
print('\n\n\n1.')
df = pd.read_csv('breast_cancer.csv')

#1.2
print('\n\n\n2.')
print(df.head())

#1.3
print('\n\n\n3.')
df['diagnosis'] = LabelEncoder().fit_transform(df['diagnosis'])
print(df.head())

#1.4
print('\n\n\n4.')
inputs = df.drop(['diagnosis', 'id', 'Unnamed: 32'], axis=1)
target = df['diagnosis']
#print(inputs, target)



#2.5
print('\n\n\n5.')
X = inputs.values
y = target.values

kfold = KFold(n_splits=5, shuffle=True)
accuracies = []

for train_idx, test_idx in kfold.split(X, y):
    x_train, x_test, y_train, y_test = X[train_idx], X[test_idx], y[train_idx], y[test_idx]
    clf = DecisionTreeClassifier()
    clf.fit(x_train, y_train)
    y_pred = clf.predict(x_test)
    accuracy = accuracy_score(y_test, y_pred)
    accuracies.append(accuracy)

print('Accuracy across folds: {}\n'.format(accuracies))
print('Mean accuracy: {}'.format(np.mean(accuracies)))


#3.6
print('\n\n\n6.')
X = normalize(X)

#3.7
print('\n\n\n7.')
x_train, x_test, y_train, y_test = train_test_split(X, y)

#3.8
print('\n\n\n8.')
clf = GaussianNB()
clf.fit(x_train, y_train)
y_pred = clf.predict(x_test)

#3.9
print('\n\n\n9.')
nb_accuracy = accuracy_score(y_test, y_pred)
print('Naive Bayes Accuracy: {}'.format(nb_accuracy))
print('f1-score: {}'.format(f1_score(y_test, y_pred)))
print('Precision Score: {}'.format(precision_score(y_test, y_pred)))
print('Confusion matrix: \n{}'.format(confusion_matrix(y_test, y_pred)))
print('Classification report: \n{}'.format(classification_report(y_test, y_pred)))




#4.10
print('\n\n\n10.')
clf = KNeighborsClassifier()        # defaults to k=5
clf.fit(x_train, y_train)
y_pred = clf.predict(x_test)

#4.11
print('\n\n\n11.')
kNN_accuracy = accuracy_score(y_test, y_pred)
print('kNN Accruacy: {}'.format(kNN_accuracy))

#4.12
print('\n\n\n12.')
if(nb_accuracy > kNN_accuracy):
    print('The Naive Bayes Classifier is more accurate')
elif(nb_accuracy < kNN_accuracy):
    print('The kNN Classifier is more accurate')
else:
    print('Both classifiers have the same accuracy')