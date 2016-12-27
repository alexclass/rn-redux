import React, { Component } from 'react';

import { Button, Card, CardSection, Input } from './common';

class LoginForm extends Component {
    state = { email: '' };
    render() {
        console.log('1.LoginForm state: ', this.state)
        return (
            <Card>
                <CardSection>
                    <Input
                        label="Email"
                        placeholder="you@pointlook.com"
                        value={this.state.text}
                        onChangeText={ email => this.setState({ email }) }
                    />
                </CardSection>

                <CardSection>
                    <Button>
                        Log IN
                    </Button>
                </CardSection>
            </Card>
        );
    }
}

export default LoginForm;