import { combineReducers } from 'redux';
// import LibraryReducer from './LibraryReducer';
// import SelectionReducer from './SelectionReducer';
import AuthReducer from './AuthReducer';
import EmployeeFormReducer from './EmployeeFormReducer';
import EmployeeReducer from './EmployeeReducer';

export default combineReducers({
    // libraries: LibraryReducer,
    // selectedLibraryId: SelectionReducer
    auth: AuthReducer,
    employeeForm: EmployeeFormReducer,
    employees: EmployeeReducer
});
