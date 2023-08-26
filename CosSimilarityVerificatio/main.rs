fn dot_product(v1: &[f64], v2: &[f64]) -> Option<f64> {
    if v1.len() != v2.len() {
        None
    } else {
        let mut product = 0.0;
        for i in 0..v1.len() {
            product += v1[i] * v2[i];
        }
        Some(product)
    }
}

fn magnitude(v: &[f64]) -> f64 {
    let mut sum_of_squares = 0.0;
    for &value in v {
        sum_of_squares += value * value;
    }
    sum_of_squares.sqrt()
}

fn cosine_similarity(v1: &[f64], v2: &[f64]) -> Option<f64> {
    match dot_product(v1, v2) {
        Some(dot_product) => {
            let magnitude_product = magnitude(v1) * magnitude(v2);
            if magnitude_product == 0.0 {
                None
            } else {
                Some(dot_product / magnitude_product)
            }
        }
        None => None,
    }
}

fn main() {
    let v1 = vec![1.0, 2.0, 3.0, 8.0, 1.0, 15.5];
    let v2 = vec![4.0, 5.0, 6.0, 8.6, 10.2, 17.7];
    match cosine_similarity(&v1, &v2) {
        Some(similarity) => println!("相似度: {}", similarity),
        None => println!("无法计算相似度"),
    }
}