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
 
import { SHOW_PROFILE, HIDE_PROFILE } from '../actions/profile'

const initialState = {
	visible: false,
}

export function profileReducer( state = initialState, action = {} ) {
	switch (action.type) {
		case SHOW_PROFILE : 
			return {
				id: action.payload.id,
				name: action.payload.name,
				email: action.payload.email,
				tel: action.payload.tel,
				visible: true,
			}
		case HIDE_PROFILE:
			return initialState
		default: 
			return state
	}
} 