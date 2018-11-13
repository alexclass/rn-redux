import React, { Component } from 'react'
import {
  View,
  Text,
  StyleSheet,
} from 'react-native'
import { Grid, Col, Row } from 'react-native-easy-grid'
import Checkbox from '../components/formInput/Checkbox'

export default class CheckboxWrapper extends Component {

  state = {
      formData: {
        name: this.props.name,
        type: this.props.type,
        label: this.props.label,
        input: 'No',
      }
  }

  constructor(props) {
    super(props)
  }

  _onSelected(value) {
    const form = this.props
    let payload = {
      name: form.name,
      type: form.type,
      label: form.label,
      input: value,
    }
    this.setState({ formData: payload })
    // after that, dispatch it to redux!

  }

  render() {
    console.log(this.state.formData)
    return (
      <View style={{ marginTop: 16 }}>
        <Checkbox
          onChecked={this.state.formData.input}
          selectedValue={this._onSelected.bind(this)}
          label={this.props.label}
          options={this.props.options}
          />
      </View>
    )
  }

}