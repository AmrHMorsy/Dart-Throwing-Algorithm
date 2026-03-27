#include <random>


template<int D>
class PoissonDisk{
    
private:
    
    static float Length(const std::array<float, D>& v)
    {
        float length = 0.0f;
        
        for(int i = 0; i < D; i++)
            length += (v[i]*v[i]);
        
        return std::sqrt(length);
    }
    
    static std::array<float, D> Subtract(const std::array<float, D>& a, const std::array<float, D>& b)
    {
        std::array<float, D> c;
        
        for(int i = 0; i < D; i++)
            c[i] = a[i] - b[i];
        
        return c;
    }

    static float Random(float min, float max)
    {
        static std::default_random_engine rng(std::random_device{}());
        std::uniform_real_distribution<float> dist(min, max);
        
        return dist(rng);
    }
    
    static std::array<float, D> Random(const std::array<float, D>& min, const std::array<float, D>& max)
    {
        std::array<float, D> p;
        
        for(int i = 0; i < D; i++)
            p[i] = Random(min[i], max[i]);
        
        return p;
    }
                            
public:
    
    static std::vector<std::array<float, D>> Generate(int numSamples, int maxNumAttempts, float minDistance, const std::array<float, D>& min, const std::array<float, D>& max)
    {
        std::vector<std::array<float, D>> samples;
    
        int attempt = 0;
        while((samples.size() < numSamples) && (attempt < maxNumAttempts)){
            std::array<float, D> point = Random(min, max);
            
            bool approved = true;
            for(int i = 0; i < samples.size(); i++){
                if(Length(Subtract(point, samples[i])) < minDistance){
                    approved = false;
                    break;
                }
            }
            if(approved)
                samples.push_back(point);
                
            attempt++;
        }
    
        return samples;
    }
};
