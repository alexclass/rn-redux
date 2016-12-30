import firebase from 'firebase';

import {
  EMAIL_CHANGED,
  PASSWORD_CHANGED,
  LOGIN_USER_SUCCESS,
  LOGIN_USER_FAIL
} from './types';

export const selectLibrary = (libraryId) => {
    console.log('1.actions libraryId: ', libraryId);
    return {
        type: 'select_library',
        payload: libraryId
    };
};

export const emailChanged = (text) => {
  console.log('1.actions emailChanged: ', text);
  return {
    type: EMAIL_CHANGED,
    payload: text
  };
};

export const passwordChanged = (text) => {
  console.log('1.actions passwordChanged: ', text);
  return {
    type: PASSWORD_CHANGED,
    payload: text
  };
};

export const loginUser = ({ email, password }) => {
  return (dispatch) => {
    firebase.auth().signInWithEmailAndPassword(email, password)
    .then(user => {
      console.log('1.actions loginUser signInWithEmailAndPassword: ', user);
      loginUserSuccess(dispatch, user);
    })
    .catch(() => {
        firebase.auth().createUserWithEmailAndPassword(email, password)
        .then(user => {
          console.log('2.action loginUser createUserWithEmailAndPassword: ', user);
          loginUserSuccess(dispatch, user);
        })
        .catch((error) => {
          console.log('3.action loginUserFail error: ', error);
          loginUserFail(dispatch, error);
        });
    });
  };
};

const loginUserFail = (dispatch, error) => {
  dispatch({
    type: LOGIN_USER_FAIL,
    payload: error.message
  });
};

const loginUserSuccess = (dispatch, user) => {
  dispatch({
    type: LOGIN_USER_SUCCESS,
    payload: user
  });
};
