import React, { Component } from 'react';

import { Button, Card, CardSection, Input } from './common';

class LoginForm extends Component {
    state = { text: '' };
    render() {
        console.log('1.LoginForm state: ', this.state)
        return (
            <Card>
                <CardSection />
                    <Input
                        label="Email"
                        value={this.state.text}
                        onChangeText={ text => this.setState({ text })}
                    />
                <CardSection />

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