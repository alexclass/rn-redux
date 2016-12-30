import {
  EMAIL_CHANGED,
  PASSWORD_CHANGED
} from '../actions/types';

const INITIAL_STATE = {
  email: '',
  password: ''
};

export default (state = INITIAL_STATE, action) => {
  switch (action.type) {
    case EMAIL_CHANGED:
      console.log('1.AuthReducer switch action: ', action);
      return { ...state, email: action.payload };

      case PASSWORD_CHANGED:
          console.log('2.AuthReducer switch action: ', action);
      return { ...state, password: action.payload };

    default:
      console.log('Z.AuthReducer switch default: ', action);
      return state;
  }
};
