import firebase from 'firebase';
import { Actions } from 'react-native-router-flux';
import {
  EMPLOYEE_UPDATE,
  EMPLOYEE_CREATE
} from './types';

export const employeeUpdate = ({ prop, value }) => {
  console.log('1.EmployeeAction prop: ', prop, ' value: ', value);
  return {
    type: EMPLOYEE_UPDATE,
    payload: { prop, value }
  };
};

export const employeeCreate = ({ name, phone, shift }) => {
  console.log('1.EmployeeAction name: ', name, ' phone: ', phone, ' shift: ', shift);

  const { currentUser } = firebase.auth();
  return (dispatch) => {
    firebase.database().ref(`/users/${currentUser.uid}/employees`)
      .push({ name, phone, shift })
      .then(() => {
        dispatch({ type: EMPLOYEE_CREATE });
        Actions.employeeList({ type: 'reset' });
      });
  };

  // return {
  //   type: EMPLOYEE_CREATE,
  //   payload: { name, phone, shift }
  // };
};
