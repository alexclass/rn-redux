import React, { Component } from 'react';
import { Text } from 'react-native';
import { Card, CardSection, Input, Button } from './common';

class LoginForm extends Component {
  render() {
    return (
      <Card>
        <CardSection>
          <Input
            label="Email"
            placeholder="alex@pointlook.com"
          />
        </CardSection>

        <CardSection>
          <Input
            label="Password"
            placeholder="password"
          />
        </CardSection>

        <CardSection>
          <Button>
            LOGIN
          </Button>
        </CardSection>
      </Card>
    );
  }
}

export default LoginForm;
