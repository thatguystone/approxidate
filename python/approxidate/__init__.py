import datetime
import typing
import time

import approxidate._c

DateType = typing.Union[
    datetime.date,
    datetime.datetime,
    datetime.time,
    float,
    None,
]


def _mktime(
    d: datetime.date,
    t: datetime.time,
    tzinfo: typing.Optional[datetime.tzinfo],
) -> float:
    dt = datetime.datetime.combine(d, t, tzinfo)
    return time.mktime(dt.timetuple())


def approx(date: str, *, relative_to: DateType = None) -> float:
    """
    Get a unix timestamp from an arbitrary date string.

    If `relative_to` is None, and the given date string is missing date or time,
    now will be used. Otherwise, the missing units will be filled in from the
    date/time represented by relative_to.

    If `relative_to` is a float, it's treated as a unix timestamp.
    """

    if isinstance(relative_to, datetime.datetime):
        relative_to = _mktime(
            relative_to.date(), relative_to.time(), relative_to.tzinfo
        )

    if isinstance(relative_to, datetime.date):
        relative_to = _mktime(relative_to, datetime.datetime.now().time(), None)

    if isinstance(relative_to, datetime.time):
        relative_to = _mktime(datetime.date.today(), relative_to, None)

    return approxidate._c.approx(date, relative_to)
