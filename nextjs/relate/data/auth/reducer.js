import { SESSION_LOGIN, SESSION_LOGOUT } from './actions';

const initialState = {
  loggedIn: false,
  token: null,
};

export default (state = initialState, action) => {
  switch (action.type) {
    case SESSION_LOGIN:
      return {
        ...state,
        token: action.token,
        loggedIn: Boolean(action.token),
      };

    case SESSION_LOGOUT:
      return {
        ...state,
        token: null,
        loggedIn: false,
      };

    default:
      return state;
  }
};
