import gql from 'graphql-tag';
import { graphql } from 'react-apollo';
import React from 'react';

import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  ScrollView,
  NavigatorIOS,
  ToastAndroid,
  TouchableHighlight,
  WebView,
  ListView,
} from 'react-native';

import _ from 'lodash';

import InfiniteScrollView from 'react-native-infinite-scroll-view';

const IssueCommentsQuery = gql`
  query GetRepositoryIssues($id: ID!, $after: String) {
    node(id: $id) {
      ... on Issue {
        comments(first: 10, after: $after) {
          edges {
            node {
              id
              body
              author {
                login
              }
            }
            cursor
          }
          pageInfo {
            hasNextPage
          }
        }
      }
    }
  }
`;

const withIssueComments = graphql(IssueCommentsQuery, {
  options: ({id, navigation}) => {
    // ToastAndroid.show(JSON.stringify(navigation), ToastAndroid.LONG);
    return ({
      variables: {
        id: navigation.state.params.id,
        after: null,
      }
    });
  },
  props: ({ data, ownProps }) => {
    if (data.loading) {
      return { loading: true, fetchNextPage: () => {} };
    }

    if (data.error) {
      console.log(data.error);
    }

    // ToastAndroid.show(JSON.stringify(data), ToastAndroid.LONG);

    const fetchNextPage = () => {
      return data.fetchMore({
        variables: {
          after: _.last(data.node.comments.edges).cursor,
        },
        updateQuery: (previousResult, { fetchMoreResult }) => {
          return {
            node: {
              comments: {
                // Append new comments to the end
                edges: [...previousResult.node.comments.edges, ...fetchMoreResult.data.node.comments.edges],
                pageInfo: fetchMoreResult.data.node.comments.pageInfo,
              }
            }
          }
        }
      })
    }

    return {
      comments: data.node.comments.edges.map(({ node }) => node),
      hasNextPage: data.node.comments.pageInfo.hasNextPage,
      fetchNextPage,
    };
  }
});

class Issue extends React.Component {
  constructor(props) {
    super();

    const ds = new ListView.DataSource({rowHasChanged: (r1, r2) => r1 !== r2});

    this.state = {
      dataSource: ds.cloneWithRows(props.comments || []),
    };
  }

  componentWillReceiveProps(newProps) {
    if (newProps.loading) { return; }

    this.setState({
      dataSource: this.state.dataSource.cloneWithRows(newProps.comments)
    })
  }

  render() {
    const { comments, hasNextPage, loading, fetchNextPage } = this.props;

    return (
      <View style={{flex: 1}}>
        <ListView
          renderScrollComponent={props => <InfiniteScrollView {...props} />}
          dataSource={this.state.dataSource}
          renderRow={(comment) => {
            return (
              <View key={comment.id}>
                <Text style={styles.commentAuthor}>
                  {comment.author.login}
                </Text>
                <Text style={styles.commentBody}>
                  {comment.body}
                </Text>
              </View>
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

export default withIssueComments(Issue);

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
  commentAuthor: {
    fontWeight: 'bold',
    fontSize: 20,
    padding: 10,
  },
  commentBody: {
    fontSize: 18,
    padding: 10,
    paddingBottom: 30,
  }
});
