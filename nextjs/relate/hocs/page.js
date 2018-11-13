import { compose } from 'redux';
import withAnalytics from './withAnalytics';
import withAuth from './withAuth';
import withData from './withData';
import withIntl from './withIntl';
import withLayout from './withLayout';
import withStyle from './withStyle';

export const pageWithoutLayout = compose(
  withData,
  withAuth,
  withIntl,
  withAnalytics,
  withStyle,
);

export default compose(
  pageWithoutLayout,
  withLayout,
);
