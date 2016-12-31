import firebase from 'firebase';
import { Actions } from 'react-native-router-flux';
import {
  EMAIL_CHANGED,
  PASSWORD_CHANGED,
  LOGIN_USER_SUCCESS,
  LOGIN_USER_FAIL,
  LOGIN_USER
} from './types';

export const emailChanged = (text) => {
  return {
    type: EMAIL_CHANGED,
    payload: text
  };
};

export const passwordChanged = (text) => {
  return {
    type: PASSWORD_CHANGED,
    payload: text
  };
};

export const loginUser = ({ email, password }) => {
  return (dispatch) => {
    dispatch({ type: LOGIN_USER });

    const errorMessage = {
      WRONG_EMAIL_PASSWORD: "Login Error wrong email or password",
      ACCOUNT_CREATE: "Login Error Creation"
    }
    firebase.auth().signInWithEmailAndPassword(email, password)
      .then(user => {
        console.log('1.loginUser signInWithEmailAndPassword success user: ', user);
        loginUserSuccess(dispatch, user);
      })
      .catch((errorLogin) => {
        console.log('2.loginUser signInWithEmailAndPassword error: ', errorLogin);
        loginUserFail(dispatch, errorLogin);
        // error login -> try create account
        firebase.auth().createUserWithEmailAndPassword(email, password)
          .then(user => {
            console.log('3.loginUser createUserWithEmailAndPassword success user: ', user);
            loginUserSuccess(dispatch, user);
          })
          .catch((errorCreate) => {
            console.log('4.loginUser createUserWithEmailAndPassword error: ', errorCreate);
            loginUserFail(dispatch, errorCreate);
          });
      });
  };
};

const loginUserFail = (dispatch, error) => {
  dispatch({ type: LOGIN_USER_FAIL, payload: error.message });
};

const loginUserSuccess = (dispatch, user) => {
  dispatch({
    type: LOGIN_USER_SUCCESS,
    payload: user
  });

  Actions.main();
};
