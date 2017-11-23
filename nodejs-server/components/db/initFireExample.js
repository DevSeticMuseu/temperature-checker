var serviceAccount = require('./serviceAccountKeyExample.json');

firebase.initializeApp({
  credential: firebase.credential.cert(serviceAccount),
  databaseURL: 'https://<PROJECT_ID>.firebaseio.com'
});