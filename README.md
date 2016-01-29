Vector Calc (due: 2016-02-04)
===
<p><strong>Submit a working C++ program which computes vector operations given a list of variables and operations.</strong></p>
The program should:
 * read from standard in (<code>cin</code>)
 * output to standard out (<code>cout</code>)
 * implement a vector2 class with overloaded operators.

<h2>Input</h2>
<p>Input begins with vector definitions on each line with the format <code>name x y</code> where:
</p><ul>
	<li><code>name</code> name of the variable. Contains no spaces, reserved operators, and numbers</li>
	<li><code>x</code> x-coordinate of the vector</li>
	<li><code>y</code> y-coordinate of the vector</li>
</ul>
<p></p>
<p>
Vector definitions end with a line containing <code>=</code>, followed by computation lines until the end of file. Each computation line may contain the following:
</p><ul>
	<li>Scalar -- Represented by a number.</li>
	<li>Vector -- Represented by a name listed in the variable definition. All vectors are stated as names and never as bare scalars.</li>
	<li>Operators -- Allowed operators, with their operations are (in addition to scalar <code>+ - / *</code> operations):
		<ul>
			<li><code>+</code> -- Vector addition.</li>
			<li><code>-</code> -- Vector subtraction.</li>
			<li><code>*</code> -- Scalar multiplication (when either one is a scalar).</li>
			<li><code>/</code> -- Scalar division (when the denominator is a scalar).</li>
			<li><code>*</code> -- Dot product (when both are vectors).</li>
			<li><code>%</code> -- Cross product.</li>
			<li><code>()</code> -- Opening and closing parenthesis.</li>
		</ul>
		Note that all operations are LEFT-ASSOCIATIVE (i.e. `a op b op c` is equivalent to `((a op b) op c)`.
	</li>
</ul>
<p>
Juxtaposing is the same as scalar multiplication. That is, scalar multiplication may be done with or without the <code>*</code> symbol (e.g. <code>3a</code>, <code>3 * a</code>, <code>a * 3</code>, <code>a3</code> are the same). The same cannot be said for dot products.
</p>

<p>
For CS majors, expect the computation lines to be full-blown expressions like <code>(1 + 3 * 2)(a + b) * 3a</code> while for non-CS majors, the computations will be restricted to <code>operand operator operand</code> format like <code>a + b</code> and <code>a * b</code>.
</p>

<h2>Output</h2>
For each computation line, output the result of the computation followed by a new line. If the result is an invalid computation, output <code>INVALID</code> instead.

<h2>Sample Input/Output</h2>
(check the `test` directory for more cases!)
<pre><code>a 1 1
b 2 3
c 1.0 -1.5
=
a + b
a * c
2a % b
a * c + b
</code></pre>

will output:
<code><pre>3 4
-0.5
4
INVALID
</pre></code>
