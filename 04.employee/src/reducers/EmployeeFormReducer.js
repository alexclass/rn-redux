import {
  EMPLOYEE_UPDATE
} from '../actions/types';

const INITIAL_STATE = {
  name: '',
  phone: '',
  shift: ''
};

export default (state = INITIAL_STATE, action) => {
  switch (action.type) {
    case EMPLOYEE_UPDATE:
      console.log('1.EmployeeFormReducer action: ', action);
      // action.payload === { prop: 'name', value: 'jane'}
      // const newState = {};
      // newState[action.payload.prop] = action.payload.value;

      return { ...state, [action.payload.prop]: action.payload.value };
    default:
      return state;
  }
};
