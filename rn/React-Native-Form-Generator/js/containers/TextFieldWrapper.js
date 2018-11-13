import React, { Component } from 'react'
import {
  StyleSheet,
  View,
} from 'react-native'
import TextField from '../components/formInput/Textfield'

export default class TextFieldWrapper extends Component {

  state = { formData: null }

  constructor(props) {
    super(props)
  }

  _onChangeText(text) {
    const form = this.props
    let payload = {
      name: form.name,
      type: form.type,
      label: form.label,
      input: text,
    }
    this.setState({ formData: payload })
    // after that, dispatch it to redux!
  }

  render() {
    return (
      <View style={{ marginTop: 16 }}>
        <TextField
          onChangeText={(text) => this._onChangeText(text)}
          placeholder={this.props.placeholder}
          label={this.props.label}
          />
      </View>
    )
  }
}