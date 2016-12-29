
export default (state = null, action) => {
    console.log('1.SelectionReducer action: ', action);
    switch (action.type) {
        case 'select_library':
            console.log('2.SelectionReducer switch action.type: ', action.type);
            return action.payload;
        default:
            return state;
    }
};