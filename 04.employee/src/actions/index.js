import {
  EMAIL_CHANGED,
  PASSWORD_CHANGED 
} from './types';

export const selectLibrary = (libraryId) => {
    console.log('1.actions libraryId: ', libraryId);
    return {
        type: 'select_library',
        payload: libraryId
    };
};

export const emailChanged = (text) => {
  console.log('2.actions emailChanged: ', text);
  return {
    type: EMAIL_CHANGED,
    payload: text
  };
};

export const passwordChanged = (text) => {
  console.log('3.actions passwordChanged: ', text);
  return {
    type: PASSWORD_CHANGED,
    payload: text
  };
};
