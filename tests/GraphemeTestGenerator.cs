using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;

namespace GraphemeTestGenerator
{
    internal class GraphemeCluster
    {
        public List<int> Codepoints = new List<int>();
    }

    internal class Testcase
    {
        public string Name = "";
        public List<GraphemeCluster> Clusters = new List<GraphemeCluster>();
        public override string ToString()
        {
            return Name;
        }

        public string AsDoctest()
        {
            var result = new StringBuilder();
            result.AppendFormat("TEST_CASE(\"{0}\")\n{{\n", Name);

            result.Append("\tstd::vector<size_t> expected{");
            foreach (var cluster in Clusters)
            {
                result.Append(cluster.Codepoints.Count + ",");
            }
            result.Remove(result.Length - 1, 1);

            result.Append("};\n");
            
            result.Append("\tstd::vector<int> input{");
            result.Append(string.Join(",",Clusters.SelectMany(cluster => cluster.Codepoints).Select(b => "0x"+b.ToString("x8"))));
            result.Append("};\n");
            result.Append("\tCHECK(expected == segmentate(input));\n}\n");
            
            return result.ToString();
        }
    }

    internal class Program
    {
        public static void Main(string[] args)
        {
            var lines = System.IO.File.ReadAllLines("GraphemeBreakTest.txt");
            var testAndComment = lines.Where(line => line[0] != '#').Select(line => line.Split('#'));
            var tests = testAndComment.Select(tac => Transform(tac[0], tac[1]));
            var testStrings = tests.Select(test => test.AsDoctest()).ToList();
            System.IO.File.WriteAllLines("tests.txt", testStrings);
        }

        public static Testcase Transform(string str, string name)
        {
            var clusters = new List<GraphemeCluster>();
            var currentCluster = new GraphemeCluster();
            foreach (var token in str.Trim().Split(' ').Select(s => s.Trim()).ToArray())
            {
                if (token == "÷")
                {
                    clusters.Add(currentCluster);
                    currentCluster = new GraphemeCluster();
                }
                else if (int.TryParse(token, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out int codepoint))
                {
                    currentCluster.Codepoints.Add(codepoint);
                }
            }
            clusters.Add(currentCluster);
            clusters.RemoveAt(0);
            clusters.RemoveAt(clusters.Count - 1);
            return new Testcase{Clusters = clusters, Name = name};
        }


    }
}
