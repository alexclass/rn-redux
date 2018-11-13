/**
 * Example for Integration Apollo Client and Redux
 * https://github.com/Thunderbird7/React-Native-GraphQL-Apollo-Client
 *
 * Yuttana K.
 * Mobile Engineer
 * Jitta.com
 *
 * @flow
 */
 
export const SHOW_PROFILE = 'SHOW_PROFILE'
export const HIDE_PROFILE = 'HIDE_PROFILE'

export function showProfile(profileData) {
	return dispatch => {
		dispatch({ type: SHOW_PROFILE, payload: profileData })
	}
}

export function hideProfile() { 
	return dispatch => {
		dispatch({ type: HIDE_PROFILE })
	}
}