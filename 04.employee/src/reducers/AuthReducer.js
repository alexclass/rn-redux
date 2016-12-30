import {
  EMAIL_CHANGED,
  PASSWORD_CHANGED,
  LOGIN_USER_SUCCESS,
  LOGIN_USER_FAIL
} from '../actions/types';

const INITIAL_STATE = {
  email: '',
  password: '',
  user: null,
  error: ''
};

export default (state = INITIAL_STATE, action) => {
  switch (action.type) {
    case EMAIL_CHANGED:
      console.log('1.AuthReducer switch action: ', action);
      return { ...state, email: action.payload };

    case PASSWORD_CHANGED:
      console.log('2.AuthReducer switch action: ', action);
      return { ...state, password: action.payload };

    case LOGIN_USER_SUCCESS:
      console.log('3.AuthReducer switch action: ', action);
      return { ...state, user: action.payload, error: '' };

    case LOGIN_USER_FAIL:
      console.log('4.AuthReducer switch action: ', action);
      return { ...state, error: action.payload, password: '' };

    default:
      console.log('Z.AuthReducer switch default: ', action);
      return state;
  }
};
