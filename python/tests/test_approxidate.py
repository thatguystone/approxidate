import datetime
import time
import unittest

import approxidate


class TestApproxidate(unittest.TestCase):
    def test_basic(self):
        self.assertEqual(
            approxidate.approx("2020-01-01 13:05:17.321 PST"), 1577912717.321
        )
        self.assertEqual(
            approxidate.approx("2020-01-01 13:05:17.321 PDT"), 1577909117.321
        )

    def test_relative(self):
        rel = datetime.datetime(2020, 1, 1, 12, 30, 17)

        self.assertEqual(
            approxidate.approx("2020-01-01", relative_to=rel), rel.timestamp()
        )
        self.assertEqual(
            approxidate.approx("12:30:17", relative_to=rel), rel.timestamp()
        )

        self.assertEqual(
            approxidate.approx("12:30:17", relative_to=rel.date()), rel.timestamp()
        )
        self.assertEqual(
            approxidate.approx("2020-01-01", relative_to=rel.time()), rel.timestamp()
        )
