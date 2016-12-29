
export const selectLibrary = (libraryId) => {
    console.log('1.action index libraryId: ', libraryId);
    return {
        type: 'select_library',
        payload: libraryId
    };
};