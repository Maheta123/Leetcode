
/*

Submitted by Samy Vilar <samy_vilar> on 03/27/2026

Given the modest constraints apply a BFS approach;
though before we begin (pre-)calculate all "bases"
for any possible item we could be given;
essentially we will let the base of some number x
be the product among its "sole" prime factors
i.e. for p1^k1*p2^2 -> p1*p2*...
Given for any composite to be reachable we had
to had to reach at the very least either one
of its primes factors or some "neighbor" at
either side w/i nums;

Using the bases along w/ all the auxillary 
properties determined through a linear sieve
we will group all indices by their prime factors
representing a "subset" of the edges;

Given this subset apply BFS from 0, taking care
to always consider either or both neighbors;

Assuming no item exceeds M and the distribution
of primes this would take O(M) pre-processing
time/additional-space w/ each subsequent
query taking ~O(n * ln(M)) time/additional-space

*/

#pragma GCC target("abm,bmi,bmi2,avx,avx2,tune=znver5")
__attribute__((no_sanitize("all")))
unsigned minJumps(unsigned *nums, size_t cnt) {
    static unsigned char
        tails[1000001],
        seen[100002] = {[0] = 1};

    static unsigned
        bases[1000001] = {[1] = 1},
        units[1000001],
        pending[100001],
        edges[700000],
        forward[700000],
        indices[1000001];

    size_t
        at, others, tail, next;

    if (bases[2] == 0) {                
        // Pre-calculate all bases and unit/least prime factors
        unsigned
            primes[72300];
        
        size_t
            to;

        next = 0;
        at = 2; do {
            if ((tail = tails[at]) == 0) 
                primes[(tail = ++next) - 1] 
                    = bases[at] = units[at] = at;

            to = at + at;
            others = 1; do {
                tails[to] = others;
                if (tail == others) {
                    bases[to] = bases[at];
                    units[to] = units[at];
                    break ;
                }
                bases[to] = primes[others - 1] * bases[at];
                units[to] = primes[others - 1];
            } while ((to = primes[others++] * at) < 1000001);
        } while (++at < 500001);

        do 
            if (tails[at] == 0)
                bases[at] = units[at] = at;
        while (++at < 1000001);
    }

    --nums;
    tail = 0;
    at = cnt; do { // gather all edges "grouped" by each base prime factor
        unsigned
            item = bases[nums[at]]; // remove all "duplicate" prime factors;
        
        for (; item != 1; item /= units[item]) { // "hybrid" chain/link-list of edges
            edges[++tail] = at;
            forward[tail] = indices[units[item]];
            indices[units[item]] = tail;            
        }
    } while (--at);

    memset(&seen[1], 0, cnt * sizeof(seen[0]));
    seen[pending[0] = 1] = seen[cnt + 1] = 1;
        
    unsigned steps = 0;    
    for (at = 0, next = 1 ; ; steps++) { // Apply BFS 
        if (seen[cnt]) {
             at = cnt; do {
                unsigned
                    item = bases[nums[at]];
                
                for (; item != 1; item /= units[item]) 
                    indices[units[item]] = 0; // reset/clear link-list
            } while (--at);

            return steps;
        }

        tail = next;
        do {
            if ((others = indices[nums[pending[at]]])) {
                // to avoid redudandant operations/considerations
                // "remove" all previoulsy considered "prime" edges;
                indices[nums[pending[at]]] = 0; do  
                    if (seen[edges[others]] == 0)   
                        seen[pending[next++] = edges[others]] = 1;            
                while ((others = forward[others]));
            }

            if (seen[pending[at] + 1] == 0) 
                seen[pending[next++] = pending[at] + 1] = 1;

            if (seen[pending[at] - 1] == 0)
                seen[pending[next++] = pending[at] - 1] = 1;
        } while (++at < tail);
    }
}