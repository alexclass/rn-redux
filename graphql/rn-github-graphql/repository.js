import gql from 'graphql-tag';
import { graphql } from 'react-apollo';
import React from 'react';
import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  ScrollView,
  ToastAndroid,
  TouchableHighlight,
  WebView,
  ListView,
} from 'react-native';

import _ from 'lodash';

import InfiniteScrollView from 'react-native-infinite-scroll-view';


GetRepositoryIssuesQuery = gql`
  query GetRepositoryIssues($states: [IssueState!], $name: String!, $login: String!, $before: String) {
    repositoryOwner(login: $login) {
      repository(name: $name) {
        issues(last: 25, states: $states, before: $before) {
          edges {
            node {
              id
              title
            }
          	cursor
          }
          pageInfo {
            hasPreviousPage
          }
        }
      }
    }
  }
`;

const withIssues = graphql(GetRepositoryIssuesQuery, {
  options: ({ login, name }) => ({
    variables: {
      states: ['OPEN'],
      login,
      name,
      before: null,
    }
  }),
  props: ({ data }) => {
    if (data.loading) {
      return { loading: true, fetchNextPage: () => {} };
    }

    if (data.error) {
      console.log(data.error);
    }

    const fetchNextPage = () => {
      return data.fetchMore({
        variables: {
          before: _.first(data.repositoryOwner.repository.issues.edges).cursor,
        },
        updateQuery: (previousResult, { fetchMoreResult }) => {
          return {
            repositoryOwner: {
              repository: {
                issues: {
                  // Append new issues to the front of the list, since we're
                  // paginating backwards
                  edges: [
                    ...fetchMoreResult.data.repositoryOwner.repository.issues.edges,
                    ...previousResult.repositoryOwner.repository.issues.edges,
                  ],
                  pageInfo: fetchMoreResult.data.repositoryOwner.repository.issues.pageInfo,
                }
              }
            }
          }
        }
      })
    }

    return {
      // We don't want our UI component to be aware of the special shape of
      // GraphQL connections, so we transform the props into a simple array
      // directly in the container. We also reverse the list since we want to
      // start from the most recent issue and scroll down
      issues: [...data.repositoryOwner.repository.issues.edges.map(({ node }) => node)].reverse(),
      hasNextPage: data.repositoryOwner.repository.issues.pageInfo.hasPreviousPage,
      fetchNextPage,
    };
  },
});

class Repository extends React.Component{
  constructor(props) {
    super();

    const ds = new ListView.DataSource({rowHasChanged: (r1, r2) => r1 !== r2});

    this.state = {
      dataSource: ds.cloneWithRows(props.issues || []),
    };
  }

  componentWillReceiveProps(newProps) {
    if (newProps.loading) { return; }

    this.setState({
      dataSource: this.state.dataSource.cloneWithRows(newProps.issues)
    })
  }

  render() {
    const { issues, goToIssue, hasNextPage, fetchNextPage } = this.props;

    return (
      <View style={{flex: 1}}>
        <ListView
          renderScrollComponent={props => <InfiniteScrollView {...props} />}
          dataSource={this.state.dataSource}
          renderRow={(issue) => {
            return (
              <TouchableHighlight activeOpacity={50} underlayColor="blue" onPress={() => goToIssue(issue.id, issue.title)}>
                <Text style={styles.welcome} key={issue.id}>
                  {issue.title}
                </Text>
              </TouchableHighlight>
            )
          }}
          onLoadMoreAsync={fetchNextPage}
          canLoadMore={hasNextPage}
          enableEmptySections={true}
        />
      </View>
    );
  }
}

const IssuesWithData = withIssues(Repository);

export default IssuesWithData;

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
  welcome: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  instructions: {
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
});
