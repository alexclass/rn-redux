import React, { Component } from 'react';
import { Provider } from 'react-redux';
import { createStore } from 'redux';
import firebase from 'firebase';
import reducers from './reducers';
import LoginForm from './components/LoginForm';

const config = require('../config');

class App extends Component {
  componentWillMount() {
    // const db = firebase.initializeApp(config);
    // console.log('1.App componentWillMount db: ', db);
    firebase.initializeApp(config);
  }

  render() {
    const store = createStore(reducers);

    return (
      <Provider store={store}>
        <LoginForm />
      </Provider>
    );
  }
}

export default App;
